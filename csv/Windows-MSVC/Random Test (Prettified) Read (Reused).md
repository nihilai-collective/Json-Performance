
----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1187.7 | 0.698947 | 8689.02ms | 728486 | 40 | 6.68618e+08 | 584945 | 0.177253 | 2.08434 | 1(Win) | true |
| Jsonifier | 1123.48 | 0.353437 | 9220.07ms | 728486 | 30 | 1.43305e+08 | 618383 | 0.856257 | 2.20359 | 2(Loss) | true |
| Glaze | 1026.39 | 0.259547 | 9834.55ms | 728486 | 30 | 9.2591e+07 | 676873 | 0.0408909 | 2.412 | 3(Loss) | true |
| simdjson (ondemand) | 866.395 | 0.0822405 | 5728.72ms | 728486 | 320 | 1.39166e+08 | 801873 | 0.0937357 | 2.85748 | 4(Loss) | true |
