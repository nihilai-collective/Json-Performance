
----
### Instruments Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 32906 | 0.0453063 | 634.483ms | 213963 | 30 | 236.792 | 6201.03 | 0.210083 | 0.0749145 | 1(Win) | true |
| Glaze | 3877.4 | 0.0784219 | 5286.81ms | 213963 | 1280 | 2.18013e+06 | 52625.8 | 0.709015 | 0.638193 | 2(Loss) | true |
| simdjson (reflection) | 508.3 | 0.170292 | 5116.13ms | 213963 | 320 | 1.49546e+08 | 401438 | 0.245903 | 4.87025 | 3(Loss) | true |
