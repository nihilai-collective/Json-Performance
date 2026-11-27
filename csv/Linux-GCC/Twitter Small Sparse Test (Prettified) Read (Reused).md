
----
### Twitter Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7136.74 | 0.0728565 | 763.179ms | 3770 | 2560 | 344.874 | 503.781 | 0.0365341 | 0.780264 | 3.11353 | 0.364722 | 0.000500145 | 1.51277e-05 | 2.48674e-06 | 1(Win) | true |
| simdjson (ondemand) | 6464.7 | 0.0435704 | 774.14ms | 3770 | 2560 | 150.318 | 556.152 | 0.270103 | 0.854139 | 3.40451 | 0.34191 | 0.000470304 | 1.34698e-05 | 2.1759e-06 | 2(Loss) | true |
