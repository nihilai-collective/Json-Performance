
----
### Marine IK Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2837.34 | 0.110707 | 8370.1ms | 7351818 | 160 | 1.19739e+09 | 2.47106e+06 | 0.454027 | 0.872563 | 1(Win) | true |
| Jsonifier (two-stage) | 2755.19 | 0.198249 | 8417.23ms | 7351818 | 40 | 1.01805e+09 | 2.54474e+06 | 0.520413 | 0.898569 | 2(Loss) | true |
| simdjson (reflection) | 2588.47 | 0.168587 | 9208.88ms | 7351818 | 80 | 1.66818e+09 | 2.70864e+06 | 0.127426 | 0.956414 | 3(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 2294.95 | 0.218028 | 5025.98ms | 7351818 | 80 | 3.5494e+09 | 3.05507e+06 | 3.97528 | 1.07878 | -(Loss) | false |
| Glaze | 2099.08 | 0.265216 | 5386ms | 7351818 | 30 | 2.35425e+09 | 3.34015e+06 | 0.00191013 | 1.17945 | 5(Loss) | true |
