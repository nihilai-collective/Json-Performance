
----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1867.86 | 0.134067 | 48.9318ms | 905 | 30 | 11.5126 | 462.067 | 0.303907 | 1.25053 | 1(Win) | true |
| Glaze | 1509.33 | 0.0305155 | 60.7288ms | 905 | 320 | 9.74357 | 571.825 | 0.124757 | 1.56762 | 2(Loss) | true |
| simdjson (ondemand) | 470.481 | 0.0532368 | 187.189ms | 905 | 320 | 305.202 | 1834.45 | 0.345804 | 5.18996 | 3(Loss) | true |
