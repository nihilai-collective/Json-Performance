
----
### Twitter Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6176.93 | 0.060612 | 760.826ms | 2821 | 640 | 44.6023 | 435.542 | 0.287247 | 0.908811 | 3.53527 | 0.45693 | 0.00106345 | 9.96987e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 5285.37 | 0.0990405 | 771.562ms | 2821 | 2560 | 650.611 | 509.012 | 0.0276961 | 1.04901 | 4.067 | 0.437079 | 0.000465676 | 3.39252e-05 | 9.8314e-06 | 2(Loss) | true |
