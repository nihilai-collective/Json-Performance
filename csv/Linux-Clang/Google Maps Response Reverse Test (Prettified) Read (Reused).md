
----
### Google Maps Response Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1603.06 | 0.0790745 | 2305.67ms | 25388 | 320 | 45643.8 | 15103.6 | 0.0190937 | 3.22111 | 14.4705 | 2.8209 | 0.00699875 | 7.1392e-06 | 1.10781e-06 | 1(Win) | true |
| simdjson (ondemand) | 1456.43 | 0.0173721 | 2436.41ms | 25388 | 4890 | 40784.2 | 16624.1 | 0.0404405 | 3.5412 | 15.5604 | 2.76524 | 0.0064878 | 1.48936e-05 | 4.96185e-06 | 2(Loss) | true |
