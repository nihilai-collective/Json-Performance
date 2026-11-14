
----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2638.53 | 0.0224569 | 1693.34ms | 25388 | 4890 | 20765.5 | 9176.29 | 0.00285419 | 1.96 | 8.84891 | 1.58969 | 0.0028677 | 8.8685e-06 | 2.02985e-06 | 1(Win) | true |
| simdjson (ondemand) | 2269.09 | 0.0734132 | 1840.69ms | 25388 | 640 | 39271.8 | 10670.3 | 0.0598852 | 2.27883 | 9.73901 | 1.58547 | 0.00358388 | 7.01611e-06 | 1.41553e-06 | 2(Loss) | true |
