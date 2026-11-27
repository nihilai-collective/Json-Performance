
----
### Github Events Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5519.91 | 0.160747 | 750.496ms | 2158 | 160 | 57.4703 | 372.837 | 0.0335154 | 1.03627 | 3.79935 | 0.550046 | 0.000923888 | 5.21316e-05 | 2.8962e-06 | 1(Win) | true |
| simdjson (ondemand) | 4774.18 | 0.217731 | 759.553ms | 2158 | 80 | 70.4753 | 431.075 | 0.0116003 | 1.17755 | 4.26877 | 0.578313 | 0.000834106 | 6.37164e-05 | 2.31696e-05 | 2(Loss) | true |
