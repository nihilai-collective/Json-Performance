
----
### Discord Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1812.51 | 0.123511 | 3480.56ms | 56369 | 2560 | 3.43533e+06 | 29659.3 | 0.0610163 | 1.36472 | 1(Win) | true |
| Jsonifier (two-stage) | 1279.53 | 0.113855 | 4763.28ms | 56369 | 2560 | 5.85766e+06 | 42013.5 | 0.180419 | 1.9335 | 2(Loss) | true |
| Glaze | 1227.48 | 0.503282 | 4857.41ms | 56369 | 160 | 7.77306e+06 | 43795 | 0.477218 | 2.01583 | 3(Loss) | true |
| simdjson (ondemand) | 1039.56 | 0.352168 | 5892.59ms | 56369 | 320 | 1.06129e+07 | 51712.2 | 0.195573 | 2.38043 | 4(Loss) | true |
