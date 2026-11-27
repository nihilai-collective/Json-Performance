
----
### Google Maps Response Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3626.8 | 0.0270425 | 1399.63ms | 25388 | 4890 | 15937.2 | 6675.83 | 0.0257665 | 1.41521 | 6.81578 | 1.18615 | 0.00326734 | 1.01009e-05 | 3.00449e-06 | 1(Win) | true |
| simdjson (ondemand) | 3338.79 | 0.0840864 | 1459.73ms | 25388 | 640 | 23796.4 | 7251.69 | 0.0142188 | 1.54476 | 7.00126 | 1.11943 | 0.00342934 | 5.29285e-06 | 0 | 2(Loss) | true |
