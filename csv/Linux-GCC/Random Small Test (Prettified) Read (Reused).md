
----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2467.74 | 0.0741754 | 1076.48ms | 8150 | 1280 | 6986.27 | 3149.62 | 0.0528059 | 2.11459 | 9.01092 | 1.58822 | 0.00278834 | 2.55943e-05 | 1.05445e-06 | 1(Win) | true |
| simdjson (ondemand) | 1981.76 | 0.0282563 | 1144.99ms | 8150 | 4890 | 6005.59 | 3922 | 0.0296792 | 2.62465 | 10.159 | 1.75791 | 0.00313345 | 2.10521e-05 | 1.32987e-06 | 2(Loss) | true |
