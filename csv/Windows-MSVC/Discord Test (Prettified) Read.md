
----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1425.88 | 0.0442312 | 5616.45ms | 83958 | 1280 | 789633 | 56153.8 | 0.0959503 | 2.13072 | 1(Win) | true |
| Jsonifier | 1330.43 | 0.0462325 | 6021.81ms | 83958 | 1280 | 990942 | 60182.7 | 0.0914721 | 2.28346 | 2(Loss) | true |
| Glaze | 1321.27 | 0.0550568 | 6072.43ms | 83958 | 1280 | 1.42486e+06 | 60599.7 | 0.0378881 | 2.2994 | 3(Loss) | true |
| simdjson (ondemand) | 1032.14 | 0.0642393 | 7760.03ms | 83958 | 4890 | 1.21439e+07 | 77575.4 | 0.0701868 | 2.94344 | 4(Loss) | true |
