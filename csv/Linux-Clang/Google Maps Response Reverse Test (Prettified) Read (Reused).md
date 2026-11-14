
----
### Google Maps Response Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1614.25 | 0.0390403 | 2281.35ms | 25388 | 2560 | 87777.1 | 14998.8 | 0.0717029 | 3.1917 | 14.4737 | 2.82228 | 0.0071646 | 8.87784e-06 | 1.63094e-06 | 1(Win) | true |
| simdjson (ondemand) | 1539.4 | 0.0935171 | 2356.84ms | 25388 | 80 | 17307.3 | 15728.2 | 0.0268698 | 3.35344 | 15.5453 | 2.75835 | 0.00673005 | 1.03395e-05 | 2.46179e-06 | 2(Loss) | true |
