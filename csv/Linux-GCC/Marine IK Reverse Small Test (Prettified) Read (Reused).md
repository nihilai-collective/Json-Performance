
----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3058.81 | 0.035583 | 1394.83ms | 18245 | 4890 | 20034.4 | 5688.42 | 0.0329721 | 1.68748 | 6.68369 | 1.15106 | 0.00130239 | 3.83891e-05 | 1.97269e-05 | 1(Win) | true |
| Jsonifier | 2716.96 | 0.0530915 | 1468.43ms | 18245 | 2560 | 29594.5 | 6404.13 | 0.0517267 | 1.90304 | 6.95051 | 1.57331 | 0.001776 | 4.41902e-05 | 2.40006e-05 | 2(Loss) | true |
| simdjson (reflection) | 2626.01 | 0.176372 | 1502.06ms | 18245 | 30 | 4097.1 | 6625.93 | 0.205676 | 2.00228 | 7.87268 | 1.31746 | 0.000813008 | 5.48095e-06 | 1.82698e-06 | 3(Loss) | true |
| Glaze | 2014.21 | 0.0457765 | 1682.68ms | 18245 | 2560 | 40031.8 | 8638.52 | 0.0327402 | 2.55017 | 10.9605 | 2.12179 | 0.00340337 | 3.89233e-05 | 2.27588e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1998.34 | 0.0888091 | 1696.24ms | 18245 | 640 | 38268.8 | 8707.13 | 0.00109464 | 2.5565 | 9.566 | 1.74244 | 0.00178773 | 3.10873e-05 | 1.57577e-05 | 5(Loss) | true |
