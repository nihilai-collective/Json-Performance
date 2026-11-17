
----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1894.14 | 0.410585 | 189.734ms | 3873 | 40 | 2564.1 | 1950 | 0.340716 | 1.58105 | 1(Win) | true |
| Glaze | 1148.58 | 0.126901 | 339.71ms | 3873 | 640 | 10658.2 | 3215.78 | 0.179455 | 2.61557 | 2(Loss) | true |
| Jsonifier (two-stage) | 1028.07 | 0.127185 | 367.203ms | 3873 | 1280 | 26725.9 | 3592.73 | 0.15463 | 2.93796 | 3(Loss) | true |
| simdjson (ondemand) | 597.928 | 0.0572113 | 624.323ms | 3873 | 4890 | 61076 | 6177.3 | 0.193193 | 5.06436 | 4(Loss) | true |
