
----
### Github Events Test (Prettified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16080.4 | 0.0267922 | 1105.82ms | 65103 | 4890 | 5232.81 | 3861.05 | 0.0121543 | 0.324985 | 1.60621 | 0.0591372 | 3.11697e-05 | 4.56411e-06 | 2.28048e-06 | 1(Win) | true |
| simdjson (stage-1) | 15858.1 | 0.0271431 | 1107.11ms | 65103 | 640 | 722.769 | 3915.16 | 0.0379789 | 0.328203 | 1.67697 | 0.0621477 | 3.00965e-05 | 2.64005e-06 | 2.64005e-07 | 2(Loss) | true |
