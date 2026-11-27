
----
### Google Maps Response Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 874.58 | 0.0412768 | 2065.68ms | 11812 | 1280 | 36180.1 | 12880.2 | 0.0807817 | 5.81693 | 27.6068 | 5.56443 | 0.0142223 | 4.02133e-05 | 1.96437e-05 | 1(Win) | true |
| simdjson (ondemand) | 751.592 | 0.0362129 | 2301.99ms | 11812 | 4890 | 144051 | 14987.9 | 0.00660685 | 6.792 | 30.4015 | 5.90442 | 0.0140822 | 5.72881e-05 | 3.07476e-05 | 2(Loss) | true |
