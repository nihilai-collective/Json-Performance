
----
### Google Maps Response Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 812.55 | 0.126388 | 2161.94ms | 11812 | 640 | 196490 | 13863.5 | 0.10923 | 6.33802 | 28.5614 | 5.79275 | 0.0142866 | 2.22232e-05 | 3.83614e-06 | 1(Win) | true |
| simdjson (ondemand) | 728.324 | 0.0930133 | 2337.41ms | 11812 | 160 | 33113.8 | 15466.8 | 0.0116365 | 7.09179 | 30.846 | 6.01261 | 0.0147858 | 2.5927e-05 | 3.70386e-06 | 2(Loss) | true |
