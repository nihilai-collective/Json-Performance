
----
### Google Maps Response Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1551.02 | 0.0653984 | 2315.43ms | 25388 | 640 | 66701.3 | 15610.2 | 0.376136 | 3.2963 | 14.7301 | 2.90247 | 0.00684926 | 2.191e-05 | 1.12627e-05 | 1(Win) | true |
| simdjson (ondemand) | 1427.16 | 0.0720115 | 2444.77ms | 25388 | 1280 | 191041 | 16965.1 | 0.0658125 | 3.59237 | 15.8508 | 2.838 | 0.00645288 | 3.86809e-05 | 2.52334e-05 | 2(Loss) | true |
