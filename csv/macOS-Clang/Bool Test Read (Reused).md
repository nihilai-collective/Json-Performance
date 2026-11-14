
----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1362.2 | 0.151747 | 76.5172ms | 905 | 320 | 295.804 | 633.587 | 0.124138 | 1(Win) | true |
| Glaze | 1289.46 | 0.112703 | 71.2789ms | 905 | 640 | 364.194 | 669.331 | 0.0252181 | 2(Loss) | true |
| Jsonifier (two-stage) | 351.659 | 0.0628897 | 256.42ms | 905 | 320 | 762.366 | 2454.3 | 0.132627 | 3(Loss) | true |
| simdjson (ondemand) | 174.545 | 0.158051 | 496.635ms | 905 | 40 | 2443.08 | 4944.73 | 0.0776319 | 4(Loss) | true |
