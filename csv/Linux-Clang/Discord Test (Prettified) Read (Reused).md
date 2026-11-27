
----
### Discord Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3744.69 | 0.0914294 | 2483.56ms | 83958 | 2560 | 978375 | 21381.9 | 0.192772 | 0.660358 | 1(Win) | true |
| Jsonifier (two-stage) | 3393.05 | 0.0882619 | 2704.69ms | 83958 | 2560 | 1.11053e+06 | 23597.8 | 0.0194905 | 0.728825 | 2(Loss) | true |
| Glaze | 2354.32 | 0.107049 | 3745.47ms | 83958 | 1280 | 1.69657e+06 | 34009.3 | 0.0381712 | 1.0508 | 3(Loss) | true |
| simdjson (ondemand) | 1381.48 | 0.0821473 | 6132.46ms | 83958 | 2560 | 5.80314e+06 | 57958.6 | 0.194965 | 1.7913 | 4(Loss) | true |
