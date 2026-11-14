
----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1350.35 | 0.13808 | 1067.13ms | 4926 | 160 | 3692.12 | 3478.95 | 0.0782669 | 3.85995 | 16.5538 | 3.1758 | 0.004088 | 5.32887e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1070.44 | 0.0540582 | 1158.31ms | 4926 | 2560 | 14408.7 | 4388.64 | 0.00842978 | 4.85416 | 18.3965 | 3.42144 | 0.00454064 | 8.88145e-05 | 4.25041e-05 | 2(Loss) | true |
