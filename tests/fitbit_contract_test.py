from __future__ import annotations

from pathlib import Path
import unittest

import cbor2


REPO_ROOT = Path(__file__).resolve().parents[1]


def cbor_round_trip(payload: dict[str, object]) -> dict[str, object]:
    return cbor2.loads(cbor2.dumps(payload))


class FitbitContractTest(unittest.TestCase):
    def test_fitbit_request_payloads_round_trip_as_json_and_cbor(self) -> None:
        expectations = {
            "activities": {"fitbit.activities": ""},
            "get-body": {"fitbit.get.body": ""},
            "get-weight": {"fitbit.get.weight": "14-07-2024"},
            "get-current-weight": {"fitbit.get.current.weight": ""},
            "get-weight-goal": {"fitbit.get.weight.goal": ""},
            "create-weight": {"fitbit.create.weight": "100"},
            "create-fat": {"fitbit.create.fat": "21"},
            "create-food-log": {
                "fitbit.create.food.log": {
                    "foodId": 5678,
                    "mealTypeId": 1,
                    "amount": "5",
                    "unitId": "ml",
                }
            },
            "get-food-log": {"fitbit.food": ""},
            "get-food-goal": {"fitbit.get.food.goal": ""},
            "get-water": {"fitbit.get.water": ""},
            "create-water-log": {
                "fitbit.create.water.log": {
                    "amount": "124",
                    "unit": "ml",
                }
            },
            "get-water-goal": {"fitbit.get.water.goal": ""},
            "get-sleep": {"fitbit.get.sleep": ""},
            "get-sleep-goal": {"fitbit.get.sleep.goal": ""},
        }

        for scenario, payload in expectations.items():
            with self.subTest(scenario=scenario):
                self.assertEqual(payload, cbor_round_trip(payload))

    def test_fitbit_response_payloads_round_trip_as_json_and_cbor(self) -> None:
        expectations = {
            "activities": {
                "endpointId": "test-endpoint-id",
                "caloriesOut": 2628,
                "activityCalories": 525,
                "steps": 1698,
                "veryActiveMinutes": 0,
                "caloriesBMR": 1973,
                "sedentaryMinutes": 802,
            },
            "get-body": {
                "endpointId": "test-endpoint-id",
                "fat": 15,
                "weight": 200,
                "bmi": 25.91,
            },
            "get-weight": {
                "endpointId": "test-endpoint-id",
                "weight": 200,
                "bmi": 25.91,
            },
            "get-current-weight": {
                "endpointId": "test-endpoint-id",
                "weight": 100,
                "weightUnit": "METRIC",
            },
            "get-weight-goal": {
                "endpointId": "test-endpoint-id",
                "weightGoal": {
                    "goalType": "LOSE",
                    "startDate": "2018-06-13",
                    "startWeight": 105.28,
                    "weight": 99.79,
                    "weightThreshold": 0.05,
                },
            },
            "create-weight": {
                "endpointId": "test-endpoint-id",
                "fitbit.create.weight": {"result": "OK"},
            },
            "create-fat": {
                "endpointId": "test-endpoint-id",
                "fitbit.create.fat": {"result": "OK"},
            },
            "create-food-log": {
                "endpointId": "test-endpoint-id",
                "fitbit.create.food.log": {"result": "OK"},
            },
            "get-food-log": {
                "endpointId": "test-endpoint-id",
                "fitbit.food.log": {
                    "calories": 280,
                    "carbs": 46,
                    "fat": 3.5,
                    "fiber": 5,
                    "protein": 18,
                    "sodium": 760,
                    "water": 0,
                },
            },
            "get-food-goal": {
                "endpointId": "test-endpoint-id",
                "fitbit.food.goal": {"calories": 2910},
            },
            "get-water": {
                "endpointId": "test-endpoint-id",
                "fitbit.get.water": {"water": 0.0},
            },
            "create-water-log": {
                "endpointId": "test-endpoint-id",
                "fitbit.create.water.log": {"result": "OK"},
            },
            "get-water-goal": {
                "endpointId": "test-endpoint-id",
                "fitbit.get.water.goal": {
                    "goal": 24,
                    "startDate": "2019-03-21",
                },
            },
            "get-sleep": {
                "endpointId": "test-endpoint-id",
                "fitbit.get.sleep": {
                    "totalMinutesAsleep": 384,
                    "stagesWake": 78,
                    "totalTimeInBed": 462,
                    "stagesDeep": 104,
                    "stageLight": 205,
                    "totalSleepRecords": 1,
                    "stagesRem": 75,
                },
            },
            "get-sleep-goal": {
                "endpointId": "test-endpoint-id",
                "fitbit.get.sleep.goal": {
                    "goal.minDuration": 480,
                    "consistency.flowId": 2,
                },
            },
        }

        for scenario, payload in expectations.items():
            with self.subTest(scenario=scenario):
                self.assertEqual(payload, cbor_round_trip(payload))

    def test_fitbit_examples_keep_docs_tags(self) -> None:
        expectations = {
            REPO_ROOT / "examples" / "fitbit" / "ActivitiesJson" / "ActivitiesJson.ino": [
                "fitbit-activities-json-docs",
            ],
            REPO_ROOT / "examples" / "fitbit" / "ActivitiesCbor" / "ActivitiesCbor.ino": [
                "fitbit-activities-cbor-docs",
            ],
            REPO_ROOT / "examples" / "fitbit" / "BodyJson" / "BodyJson.ino": [
                "fitbit-get-body-json-docs",
                "fitbit-get-weight-json-docs",
                "fitbit-get-current-weight-json-docs",
                "fitbit-get-weight-goal-json-docs",
                "fitbit-create-weight-json-docs",
                "fitbit-create-fat-json-docs",
            ],
            REPO_ROOT / "examples" / "fitbit" / "BodyCbor" / "BodyCbor.ino": [
                "fitbit-get-body-cbor-docs",
                "fitbit-get-weight-cbor-docs",
                "fitbit-get-current-weight-cbor-docs",
                "fitbit-get-weight-goal-cbor-docs",
                "fitbit-create-weight-cbor-docs",
                "fitbit-create-fat-cbor-docs",
            ],
            REPO_ROOT / "examples" / "fitbit" / "FoodJson" / "FoodJson.ino": [
                "fitbit-create-food-log-json-docs",
                "fitbit-get-food-log-json-docs",
                "fitbit-get-food-goal-json-docs",
            ],
            REPO_ROOT / "examples" / "fitbit" / "FoodCbor" / "FoodCbor.ino": [
                "fitbit-create-food-log-cbor-docs",
                "fitbit-get-food-log-cbor-docs",
                "fitbit-get-food-goal-cbor-docs",
            ],
            REPO_ROOT / "examples" / "fitbit" / "WaterJson" / "WaterJson.ino": [
                "fitbit-get-water-json-docs",
                "fitbit-create-water-log-json-docs",
                "fitbit-get-water-goal-json-docs",
            ],
            REPO_ROOT / "examples" / "fitbit" / "WaterCbor" / "WaterCbor.ino": [
                "fitbit-get-water-cbor-docs",
                "fitbit-create-water-log-cbor-docs",
                "fitbit-get-water-goal-cbor-docs",
            ],
            REPO_ROOT / "examples" / "fitbit" / "SleepJson" / "SleepJson.ino": [
                "fitbit-get-sleep-json-docs",
                "fitbit-get-sleep-goal-json-docs",
            ],
            REPO_ROOT / "examples" / "fitbit" / "SleepCbor" / "SleepCbor.ino": [
                "fitbit-get-sleep-cbor-docs",
                "fitbit-get-sleep-goal-cbor-docs",
            ],
        }

        for path, tag_names in expectations.items():
            content = path.read_text(encoding="utf-8")
            for tag_name in tag_names:
                with self.subTest(path=path.as_posix(), tag_name=tag_name):
                    self.assertIn(f"// tag::{tag_name}[]", content)
                    self.assertIn(f"// end::{tag_name}[]", content)

    def test_every_fitbit_sketch_exposes_doc_tags(self) -> None:
        fitbit_sketches = sorted((REPO_ROOT / "examples" / "fitbit").glob("*/*.ino"))
        self.assertTrue(fitbit_sketches)

        for sketch in fitbit_sketches:
            content = sketch.read_text(encoding="utf-8")
            self.assertIn("// tag::fitbit-", content, sketch.as_posix())
            self.assertIn("// end::fitbit-", content, sketch.as_posix())


if __name__ == "__main__":
    unittest.main()
