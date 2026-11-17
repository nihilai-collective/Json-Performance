
----
### Github Events Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1185.45 | 0.115133 | 896.382ms | 2158 | 80 | 319.615 | 1736.08 | 0.0546912 | 4.53176 | 16.012 | 3.16914 | 0.00189411 | 8.6886e-05 | 2.31696e-05 | 1(Win) | true |
| simdjson (ondemand) | 1019.47 | 0.0971379 | 932.279ms | 2158 | 160 | 615.254 | 2018.73 | 0.0213579 | 5.24866 | 20.7535 | 3.95644 | 0.00143941 | 4.63392e-05 | 0 | 2(Loss) | true |
