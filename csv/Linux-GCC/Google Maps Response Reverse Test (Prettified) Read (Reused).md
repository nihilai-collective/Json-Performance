
----
### Google Maps Response Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1661.31 | 0.0729774 | 2234.91ms | 25388 | 1280 | 144792 | 14574 | 0.0190497 | 3.09506 | 14.187 | 2.78328 | 0.00674005 | 1.43399e-05 | 4.00041e-06 | 1(Win) | true |
| simdjson (ondemand) | 1506.52 | 0.0215135 | 2387.81ms | 25388 | 4890 | 58457.6 | 16071.4 | 0.09151 | 3.42114 | 14.9105 | 2.79569 | 0.00726218 | 2.69357e-05 | 1.21307e-05 | 2(Loss) | true |
