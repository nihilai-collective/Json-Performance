
----
### Twitter Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3949.07 | 0.0750024 | 781.232ms | 2821 | 4890 | 1276.67 | 681.254 | 0.370173 | 1.39057 | 5.43353 | 0.859624 | 0.000941884 | 4.3205e-05 | 1.63831e-05 | 1(Win) | true |
| simdjson (ondemand) | 3564.13 | 0.18882 | 788.086ms | 2821 | 640 | 1300.09 | 754.831 | 0.0546181 | 1.52526 | 6.18185 | 0.896491 | 0.000752725 | 1.27393e-05 | 5.53882e-07 | 2(Loss) | true |
