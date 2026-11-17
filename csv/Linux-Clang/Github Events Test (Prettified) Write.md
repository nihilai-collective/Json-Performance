
----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16606.9 | 0.0822921 | 1208.31ms | 78778 | 40 | 554.379 | 4523.93 | 0.183621 | 0.307313 | 1.09159 | 0.183579 | 4.66501e-05 | 8.56838e-06 | 1.58674e-06 | 1(Win) | true |
| Glaze | 4544.55 | 0.208241 | 2404.11ms | 78778 | 1280 | 1.51695e+06 | 16531.6 | 0.0839496 | 1.11306 | 3.01834 | 0.488297 | 0.000360051 | 3.48983e-05 | 1.91599e-05 | 2(Loss) | true |
