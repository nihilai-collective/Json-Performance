
----
### Canada Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 826.271 | 0.0587115 | 1364.98ms | 4630 | 1280 | 12600.1 | 5343.9 | 0.213746 | 6.19258 | 31.1596 | 5.66588 | 0.00326978 | 2.61542e-05 | 3.88094e-06 | 1(Win) | true |
| Jsonifier (generic) | 801.22 | 0.0342093 | 1368.15ms | 4630 | 4890 | 17380.2 | 5510.99 | 0.0745734 | 6.43449 | 29.5616 | 5.91642 | 0.00449642 | 5.31786e-05 | 2.27025e-05 | 2(Loss) | true |
