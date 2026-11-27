
----
### Twitter Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 890.473 | 0.0352467 | 1028.69ms | 2821 | 4890 | 5545.11 | 3021.22 | 0.153789 | 5.82396 | 24.4669 | 4.42219 | 0.0042665 | 5.12516e-05 | 1.42084e-05 | 1(Win) | true |
| simdjson (ondemand) | 392.067 | 0.0186135 | 1411.77ms | 2821 | 4890 | 7977.2 | 6861.88 | 0.0353762 | 13.1939 | 58.4885 | 11.7909 | 0.00834879 | 7.11868e-05 | 1.7398e-05 | 2(Loss) | true |
