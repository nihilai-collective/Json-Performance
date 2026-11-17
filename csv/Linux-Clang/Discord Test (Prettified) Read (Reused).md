
----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3019.48 | 0.110199 | 3061.07ms | 83958 | 2560 | 2.18604e+06 | 26517.3 | 0.0596821 | 0.819064 | 1(Win) | true |
| Jsonifier | 2333.52 | 0.217363 | 3868.14ms | 83958 | 320 | 1.78e+06 | 34312.3 | 0.0613403 | 1.06011 | 2(Loss) | true |
| Glaze | 2150.91 | 0.0728218 | 4079.13ms | 83958 | 4890 | 3.59346e+06 | 37225.5 | 0.373574 | 1.1502 | 3(Loss) | true |
| simdjson (ondemand) | 1350.45 | 0.179861 | 6424.14ms | 83958 | 160 | 1.81954e+06 | 59290.3 | 0.036523 | 1.83242 | 4(Loss) | true |
