
----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 3187.1 | 0.06003 | 1016.34ms | 9378 | 160 | 454.032 | 2806.18 | 0.131234 | 1.60987 | 7.3649 | 1.13084 | 0.00181142 | 1.33291e-05 | 4.66517e-06 | 1(Win) | true |
| Jsonifier (generic) | 3070.34 | 0.123908 | 1024.61ms | 9378 | 640 | 8337.39 | 2912.89 | 0.0486822 | 1.67409 | 7.2186 | 1.27661 | 0.00172845 | 3.38225e-05 | 2.18263e-05 | 2(Loss) | true |
