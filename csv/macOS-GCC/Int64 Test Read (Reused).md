
----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3114.93 | 0.932051 | 127.12ms | 3862 | 1280 | 155460 | 1182.4 | 0.578428 | 1(Win) | true |
| Glaze | 1431.38 | 0.487463 | 261.086ms | 3862 | 2560 | 402751 | 2573.1 | 0.0116577 | 2(Loss) | true |
| Jsonifier (two-stage) | 886.232 | 0.318728 | 417.36ms | 3862 | 2560 | 449170 | 4155.9 | 0.136967 | 3(Loss) | true |
| simdjson (ondemand) | 440.477 | 1.013 | 873.308ms | 3862 | 80 | 573969 | 8361.6 | 0.114679 | 4(Loss) | true |
