
----
### Google Maps Response Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 807.43 | 0.0237337 | 2171.2ms | 11812 | 2560 | 28067.8 | 13951.4 | 0.0760041 | 6.38694 | 28.6059 | 5.80782 | 0.0142617 | 1.80563e-05 | 1.12439e-06 | 1(Win) | true |
| simdjson (ondemand) | 733.299 | 0.0720486 | 2315.13ms | 11812 | 160 | 19600 | 15361.8 | 0.0209573 | 7.03974 | 30.7329 | 5.98468 | 0.0132662 | 4.60337e-05 | 1.21698e-05 | 2(Loss) | true |
