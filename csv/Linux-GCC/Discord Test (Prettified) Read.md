
----
### Discord Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2167.63 | 0.0864471 | 4479.54ms | 83958 | 40 | 40786.4 | 36938.3 | 0.128068 | 2.37841 | 10.2549 | 1.92422 | 0.00465352 | 3.27545e-05 | 2.02482e-05 | 1(Win) | true |
| simdjson (ondemand) | 1840.58 | 0.0504584 | 5093.95ms | 83958 | 1280 | 616726 | 43501.9 | 0.112852 | 2.76243 | 11.0768 | 1.909 | 0.0076392 | 2.30863e-05 | 1.28319e-05 | 2(Loss) | true |
