
----
### Discord Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2953.97 | 0.0393077 | 872.497ms | 4857 | 4890 | 1857.76 | 1568.06 | 0.0302589 | 1.78614 | 7.50525 | 1.32592 | 0.000450428 | 2.40414e-05 | 9.68391e-07 | 1(Win) | true |
| simdjson (ondemand) | 2267.11 | 0.0873521 | 917.739ms | 4857 | 160 | 509.632 | 2043.12 | 0.0238548 | 2.31539 | 10.2364 | 1.70558 | 0.00195723 | 1.54416e-05 | 0 | 2(Loss) | true |
