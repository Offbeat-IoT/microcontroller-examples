from pathlib import Path
import unittest


REPO_ROOT = Path(__file__).resolve().parents[1]


class WeatherContractTest(unittest.TestCase):
    def test_weather_example_requests_city_and_handles_response(self) -> None:
        sketch = (REPO_ROOT / "examples" / "weather" / "CurrentWeatherJson" / "CurrentWeatherJson.ino").read_text(
            encoding="utf-8"
        )

        self.assertIn('request["weather"]["city"] = "Copenhagen"', sketch)
        self.assertIn('response["weather.response"]', sketch)
        self.assertIn("weather-current-json-docs", sketch)


if __name__ == "__main__":
    unittest.main()
