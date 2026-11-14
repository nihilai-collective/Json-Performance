
----
### Discord Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1878.48 | 0.0193717 | 3597.6ms | 56369 | 4890 | 150283 | 28617.6 | 0.0161293 | 2.72552 | 13.1344 | 2.49882 | 0.00411835 | 1.3122e-05 | 5.63044e-06 | 1(Win) | true |
| simdjson (ondemand) | 1345.12 | 0.168805 | 4736.96ms | 56369 | 30 | 136537 | 39965 | 0.0529076 | 3.83157 | 16.6249 | 2.9803 | 0.0106507 | 2.01056e-05 | 1.53749e-05 | 2(Loss) | true |
