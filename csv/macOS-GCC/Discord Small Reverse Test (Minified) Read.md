
----
### Discord Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 579 | 0.155624 | 848.233ms | 4857 | 1280 | 198401 | 8000 | 0.0749438 | 1(Win) | true |
| simdjson (ondemand) | 154.706 | 0.120974 | 2975.39ms | 4857 | 4890 | 6.41528e+06 | 29940.6 | 0.0857084 | 2(Loss) | true |
