
----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16607.7 | 0.560801 | 749.69ms | 5094 | 4890 | 13159.1 | 292.516 | 0.416146 | 0.352097 | 1.4998 | 0.236749 | 0.000196871 | 2.8222e-05 | 1.11603e-05 | 1(Win) | true |
| simdjson (reflection) | 9089.11 | 0.100235 | 776.099ms | 5094 | 80 | 22.9619 | 534.487 | 0.170433 | 0.609016 | 2.29388 | 0.329211 | 0.000196309 | 5.39851e-05 | 1.22693e-05 | 2(Loss) | true |
| Glaze | 4882.08 | 0.0947783 | 820.815ms | 5094 | 4890 | 4349.46 | 995.072 | 0.0470367 | 1.09612 | 4.69925 | 0.724382 | 0.000197795 | 4.21122e-05 | 1.31274e-05 | 3(Loss) | true |
