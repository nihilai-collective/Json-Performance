
----
### Random Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1413.83 | 0.0826115 | 6484.21ms | 676745 | 640 | 9.10154e+07 | 456485 | 0.0892219 | 3.57661 | 16.5774 | 3.28434 | 0.00618382 | 0.0114099 | 5.43964e-06 | 1(Win) | true |
| simdjson (ondemand) | 853.953 | 0.127004 | 5092.98ms | 676745 | 30 | 2.76399e+07 | 755773 | 0.00835278 | 5.94182 | 26.9857 | 5.30236 | 0.018028 | 0.0186934 | 2.19679e-05 | 2(Loss) | true |
