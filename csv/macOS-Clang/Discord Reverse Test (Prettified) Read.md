
----
### Discord Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 692.683 | 0.941658 | 5639.04ms | 83958 | 160 | 1.89567e+08 | 115592 | 0.111437 | 1(Win) | true |
| simdjson (ondemand) | 211.903 | 0.161931 | 9918.61ms | 83958 | 640 | 2.39601e+08 | 377855 | 1.55193 | 2(Loss) | true |
