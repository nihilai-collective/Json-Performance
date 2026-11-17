
----
### Github Events Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18397.3 | 0.0601078 | 1152.28ms | 78778 | 1280 | 7712.16 | 4083.68 | 0.000612196 | 0.276439 | 0.823656 | 0.123105 | 2.55068e-05 | 2.12325e-05 | 1.25352e-05 | 1(Win) | true |
| Glaze | 6037.65 | 0.079687 | 1988.4ms | 78778 | 4890 | 480793 | 12443.4 | 0.302762 | 0.834165 | 2.80596 | 0.434093 | 8.04155e-05 | 3.38712e-05 | 2.11513e-05 | 2(Loss) | true |
| simdjson (reflection) | 636.921 | 0.113195 | 6430ms | 78778 | 2560 | 4.56388e+07 | 117956 | 0.0830247 | 7.93503 | 29.3753 | 6.6079 | 0.0317734 | 0.0179112 | 0.000287695 | 3(Loss) | true |
