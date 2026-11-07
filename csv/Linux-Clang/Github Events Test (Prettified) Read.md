
----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2261.12 | 0.0586386 | 2754.76ms | 65103 | 4890 | 1.26774e+06 | 27458.5 | 0.0414242 | 1.09377 | 1(Win) | true |
| Jsonifier STATISTICAL TIE | 1660.38 | 0.0807488 | 3745.39ms | 65103 | 2560 | 2.33399e+06 | 37393.3 | 0.00103316 | 1.48994 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1654.86 | 0.150158 | 3767.54ms | 65103 | 640 | 2.03123e+06 | 37518.1 | 0.194602 | 1.49503 | 2(Tie) | true |
| simdjson (ondemand) | 1278.29 | 0.0627465 | 4875.39ms | 65103 | 2560 | 2.37774e+06 | 48570.5 | 0.110529 | 1.93566 | 4(Loss) | true |
