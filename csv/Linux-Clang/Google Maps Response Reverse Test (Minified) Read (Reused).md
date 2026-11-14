
----
### Google Maps Response Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 818.34 | 0.0215996 | 2149.58ms | 11812 | 4890 | 43229.5 | 13765.4 | 0.0357491 | 6.30912 | 28.9064 | 5.78412 | 0.015123 | 2.25932e-05 | 2.99512e-06 | 1(Win) | true |
| simdjson (ondemand) | 720.138 | 0.0624712 | 2339.84ms | 11812 | 160 | 15279 | 15642.5 | 0.00391576 | 7.17078 | 32.4524 | 5.93371 | 0.013609 | 2.32814e-05 | 1.05825e-06 | 2(Loss) | true |
