
----
### Twitter Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4410.31 | 0.0482511 | 781.612ms | 2821 | 4890 | 423.635 | 610.007 | 0.1647 | 1.24167 | 5.16306 | 0.848635 | 0.00137705 | 2.10951e-05 | 2.10226e-06 | 1(Win) | true |
| simdjson (ondemand) | 3704.56 | 0.0614164 | 796.895ms | 2821 | 640 | 127.316 | 726.217 | 0.22059 | 1.44508 | 6.17831 | 0.884084 | 0.000833592 | 1.27393e-05 | 3.87717e-06 | 2(Loss) | true |
