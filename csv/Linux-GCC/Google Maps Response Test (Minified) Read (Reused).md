
----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2140.97 | 0.0520675 | 564.699ms | 11812 | 30 | 225.154 | 5261.53 | 0.0843304 | 1.15046 | 1(Win) | true |
| Glaze | 1786.25 | 0.150387 | 664.174ms | 11812 | 4890 | 439840 | 6306.4 | 0.321858 | 1.37973 | 2(Loss) | true |
| Jsonifier (two-stage) | 1689.06 | 0.0642733 | 701.069ms | 11812 | 30 | 551.237 | 6669.27 | 0.0599407 | 1.45987 | 3(Loss) | true |
| simdjson (reflection) | 1482.59 | 0.0856601 | 815.92ms | 11812 | 30 | 1270.82 | 7598.07 | 0.0882582 | 1.66406 | 4(Loss) | true |
| simdjson (ondemand) | 1246.51 | 0.116551 | 974.417ms | 11812 | 30 | 3328.23 | 9037.1 | 0.0236008 | 1.98065 | 5(Loss) | true |
