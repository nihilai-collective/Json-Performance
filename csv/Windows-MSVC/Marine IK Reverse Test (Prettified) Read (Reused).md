
----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2097.36 | 0.43276 | 5447.43ms | 7351818 | 80 | 1.67428e+10 | 3.34288e+06 | 0.035137 | 1.44906 | 1(Win) | true |
| Jsonifier | 2041.8 | 0.0870927 | 5583.79ms | 7351818 | 30 | 2.68316e+08 | 3.43385e+06 | 0.500802 | 1.48849 | 2(Loss) | true |
| Glaze | 1082.69 | 0.514966 | 10366.3ms | 7351818 | 80 | 8.89669e+10 | 6.47575e+06 | 0.0191713 | 2.80718 | 3(Loss) | true |
| simdjson (ondemand) | 658.13 | 0.324467 | 7677.24ms | 7351818 | 40 | 4.77933e+10 | 1.06533e+07 | 0.426966 | 4.61817 | 4(Loss) | true |
