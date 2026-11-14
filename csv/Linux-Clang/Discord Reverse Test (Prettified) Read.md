
----
### Discord Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 923.345 | 0.0404554 | 9499.03ms | 83958 | 640 | 787645 | 86715.8 | 0.0944635 | 5.55791 | 25.0738 | 5.23875 | 0.00835178 | 1.60236e-05 | 7.0906e-06 | 1(Win) | true |
| simdjson (ondemand) | 306.145 | 0.0949978 | 6848.75ms | 83958 | 640 | 3.95072e+07 | 261538 | 0.0672132 | 16.6201 | 93.9425 | 18.8216 | 0.0237212 | 7.96715e-05 | 3.56205e-05 | 2(Loss) | true |
