
----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2511.54 | 0.146684 | 4986.14ms | 94653 | 320 | 889419 | 35941.4 | 0.634886 | 0.98508 | 1(Win) | true |
| Jsonifier (two-stage) | 2168.86 | 0.11159 | 5456.07ms | 94653 | 640 | 1.38051e+06 | 41620.2 | 0.104517 | 1.14081 | 2(Loss) | true |
| Glaze | 2007.35 | 0.0536897 | 5806.02ms | 94653 | 4890 | 2.85045e+06 | 44968.8 | 0.177895 | 1.23266 | 3(Loss) | true |
| simdjson (ondemand) | 1380.13 | 0.0424019 | 7811.65ms | 94653 | 4890 | 3.76106e+06 | 65405.8 | 0.174229 | 1.79306 | 4(Loss) | true |
