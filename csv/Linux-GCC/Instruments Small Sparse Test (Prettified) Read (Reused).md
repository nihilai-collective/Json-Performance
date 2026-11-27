
----
### Instruments Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7420.13 | 0.0529163 | 822.09ms | 7932 | 640 | 186.252 | 1019.46 | 0.147661 | 0.721083 | 3.35527 | 0.428013 | 0.000509014 | 6.89454e-06 | 3.54576e-06 | 1(Win) | true |
| simdjson (ondemand) | 6936.1 | 0.0894678 | 832.387ms | 7932 | 1280 | 1218.65 | 1090.6 | 0.0846003 | 0.768883 | 3.67045 | 0.398134 | 0.000743035 | 1.05388e-05 | 5.22015e-06 | 2(Loss) | true |
