
----
### Apache Builds Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3972.82 | 0.0971633 | 778.84ms | 2632 | 640 | 241.19 | 631.811 | 0.390448 | 1.37691 | 6.03381 | 0.921733 | 0.00101218 | 1.48414e-05 | 4.15559e-06 | 1(Win) | true |
| simdjson (ondemand) | 2781.55 | 0.156606 | 805.133ms | 2632 | 40 | 79.8872 | 902.4 | 0.0110828 | 1.93523 | 7.08283 | 1.1421 | 0.00139628 | 0 | 0 | 2(Loss) | true |
