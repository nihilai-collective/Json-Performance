
----
### Twitter Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 850.354 | 0.0453152 | 1044.66ms | 2821 | 4890 | 10050.9 | 3163.76 | 0.874496 | 6.07642 | 25.0216 | 4.56363 | 0.00443881 | 0.000119974 | 5.61085e-05 | 1(Win) | true |
| simdjson (ondemand) | 386.358 | 0.0326725 | 1418.57ms | 2821 | 4890 | 25310.5 | 6963.28 | 0.00587931 | 13.3188 | 58.9234 | 11.9007 | 0.00732992 | 0.000184926 | 9.25719e-05 | 2(Loss) | true |
