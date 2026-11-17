
----
### Google Maps Response Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1649.02 | 0.0956884 | 1285.18ms | 9378 | 4890 | 131703 | 5423.54 | 0.0337957 | 3.14116 | 13.9971 | 2.72883 | 0.00580864 | 3.93821e-05 | 1.29311e-05 | 1(Win) | true |
| simdjson (ondemand) | 1538.64 | 0.0554757 | 1327.59ms | 9378 | 1280 | 13309.4 | 5812.63 | 0.0684997 | 3.36921 | 14.7413 | 2.74526 | 0.00471016 | 1.62448e-05 | 1.08299e-06 | 2(Loss) | true |
