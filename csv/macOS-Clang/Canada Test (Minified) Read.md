
----
### Canada Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 735.221 | 0.0851113 | 9208.78ms | 2251027 | 40 | 2.47036e+08 | 2.91987e+06 | 1.32914 | 1(Win) | true |
| Jsonifier (two-stage) | 644.044 | 0.753164 | 5032.5ms | 2251027 | 40 | 2.52098e+10 | 3.33323e+06 | 0.314097 | 2(Loss) | true |
| Glaze | 581.296 | 0.882066 | 5429.81ms | 2251027 | 40 | 4.24453e+10 | 3.69304e+06 | 1.61111 | 3(Loss) | true |
| simdjson (ondemand) | 539.512 | 0.0631554 | 6058.28ms | 2251027 | 30 | 1.89454e+08 | 3.97906e+06 | 0.109692 | 4(Loss) | true |
