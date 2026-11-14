
----
### Google Maps Response Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 801.965 | 0.0670098 | 1261.16ms | 4390 | 1280 | 15664.1 | 5220.46 | 0.0123148 | 6.46921 | 28.0114 | 5.64761 | 0.0116431 | 4.1287e-05 | 5.5168e-06 | 1(Win) | true |
| simdjson (ondemand) | 749.914 | 0.061049 | 1298.11ms | 4390 | 640 | 7434.36 | 5582.81 | 0.00559722 | 6.91611 | 30.1961 | 5.8426 | 0.00665433 | 2.95416e-05 | 4.27107e-06 | 2(Loss) | true |
