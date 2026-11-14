
----
### Canada Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 12132.3 | 0.0368017 | 805.246ms | 11579 | 1280 | 143.616 | 910.182 | 0.00952672 | 0.442742 | 2.126 | 0.20874 | 0.000172726 | 8.36644e-06 | 3.37356e-07 | 1(Win) | true |
| simdjson (ondemand) | 10936.9 | 0.0491479 | 811.577ms | 11579 | 4890 | 1204.14 | 1009.67 | 0.03014 | 0.489019 | 2.45064 | 0.231799 | 0.000173044 | 7.50601e-06 | 5.12175e-07 | 2(Loss) | true |
