
----
### Canada Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5750.43 | 0.0445717 | 6986.43ms | 6661989 | 80 | 1.94006e+07 | 1.10485e+06 | 0.036987 | 0.430529 | 1(Win) | true |
| Glaze | 3343.3 | 0.0303363 | 5915.63ms | 6661897 | 160 | 5.31728e+07 | 1.9003e+06 | 0.165671 | 0.740501 | 2(Loss) | true |
