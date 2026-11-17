
----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2982.62 | 0.203396 | 5344.11ms | 631514 | 80 | 1.34941e+07 | 201923 | 0.0257281 | 1.70128 | 8.25722 | 1.35256 | 0.00544772 | 6.99509e-05 | 6.62891e-05 | 1(Win) | true |
| Glaze | 2172.79 | 0.0987368 | 7220.52ms | 631514 | 640 | 4.79369e+07 | 277183 | 0.374743 | 2.32318 | 9.80782 | 1.64384 | 0.00936898 | 1.84329e-05 | 1.60156e-05 | 2(Loss) | true |
